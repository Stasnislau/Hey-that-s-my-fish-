# Testing documentation #

We performed 1000 tests of intercative mode, the results we obtained can be found in **test_results.txt** and each of the gameplays in text file in **folder games**.

To run tests, first they need to build with `./build`.
Then `./run n`, where n is the number of test you want to perform.

Additionally a directory named games is required to exist and since test only concern **inveractive mode**, they will be run only if the flag in defines.h INTERACVITE_MODE is 1.
