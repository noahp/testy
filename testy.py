#!/usr/bin/env python3
"""
run the testy test executables built from the c files being tested.

pass a list of c files you want to run.

each one is built (potentially with exploding fakes inserted for linker
undefined reference errors) and the resulting binary is run, which will execute
the testy main.
"""

import os
import sys
import subprocess
import tempfile
import re

# todo support adjusting compiler commands
# right now it assumes testy.c + testy.h are in the cwd
COMPILER = os.environ.get("CC", "gcc")
COMPILE_COMMAND = (
    COMPILER + " -Og -DTESTY_UNIT_TEST -Wl,--wrap=main testy.c {} -I. -o testy.test && ./testy.test"
)

# regex for locating linker missing definition errors
FIND_LINKER_ERRORS = re.compile(r"undefined reference to `(.*?)'")


def compile_and_run(c_file):
    """attempt to compile the file under test and run the result"""
    result = subprocess.run(
        COMPILE_COMMAND.format(c_file), capture_output=True, shell=True
    )
    if result.returncode == 0:
        print(result.stdout.decode("utf-8").strip())
        return None

    # if it failed, check if we need to generate exploding fakes
    stderr = result.stderr.decode("utf-8")
    m = FIND_LINKER_ERRORS.search(stderr)
    if not m:
        # bail, don't know what to do here
        print("unrecoverable error:")
        print(result.args)
        print(stderr)
        sys.exit(-1)

    # return list of exploding fakes
    return m.groups()


def main():
    """main cli entrance point"""
    for c_file in sys.argv[1:]:
        # run gcc and get a list of fakes needed
        fake_list = compile_and_run(c_file)

        # check if we need to re-run with autogenerated fakes
        if fake_list:

            # make the fake file
            with tempfile.NamedTemporaryFile("w", suffix=".c") as fake_file:
                fake_file.write('#include "testy.h"\n')
                fake_file.write(
                    "\n".join(["TESTY_EXPLODING_FAKE({})".format(x) for x in fake_list])
                )
                fake_file.write("\n")
                fake_file.flush()

                # try again, with exploding fakes inserted
                compile_and_run("{} {}".format(c_file, fake_file.name))


if __name__ == "__main__":
    main()