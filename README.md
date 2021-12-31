# C Sort

This code was a way for me to practice writing C code by implementing common sorting algorithms using [what I created with Typescript](https://github.com/richardwalenga/typescriptsort) as a guide. I have logging in [main.c](main.c) which times the implementations against the same large array of random ints.

## First Steps

If you don't have Ruby, install it, and then run the following command to make sure Rake is installed:
```
gem install rake
```

I don't normally program in C and rake can get the job done for the simple needs of this project. I considered using make and may switch this repo to use that build tool at a later date.

## Running

To run it, just execute this:
```
rake default && ./csort
```

For convenience I added a VSCode task called "run" which effectively does the same thing.