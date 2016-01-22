A naive implementation of the Needleman-Wunsch algorithm to align protein or nucleotide sequences.
Notice that this implementation uses a simple match-mismatch-gap scoring,
so this doesn't use a similarity matrix of DNA to calculate alignment scores.

## Usage

    $ nw input_file1 input_file2 output_file

For example:

    $ ./nw s_input1.txt s_input2.txt out.txt
    input file1:
    GGGCCCATAGCTCAGTGGTAGAGTGCCTCCTTTGCAAGGAGGATGCCCTGGGTTCGAATCCCAGTGGGTCCAT
    input file2:
    GGGCCCATAGCTCAGCCTGGGAGAGCGCCGCCCTTGCAAGGCGGAGGCCCCGGGTTCAAATCCCGGTGGGTCCAT

    ::: Alignment :::
    Initialize phase...
    Calculating alignment score...
    Traceback phase...
    Start tracebacking from mat[75,73]:
    (75,73)->(74,72)->(73,71)->(72,70)->(71,69)->(70,68)->(69,67)->(68,66)->(67,65)->(66,64)->(65,63)->(64,62)->(63,61)->(62,60)->(61,59)->(60,58)->(59,57)->(58,56)->(57,55)->(56,54)->(55,53)->(54,52)->(53,51)->(52,50)->(51,49)->(50,48)->(49,47)->(48,46)->(47,45)->(46,44)->(45,43)->(44,42)->(43,41)->(42,40)->(41,39)->(40,38)->(39,37)->(38,36)->(37,35)->(36,34)->(35,33)->(34,32)->(33,31)->(32,30)->(31,29)->(30,28)->(29,27)->(28,26)->(27,25)->(26,24)->(25,23)->(24,22)->(23,21)->(22,20)->(21,19)->(20,18)->(19,17)->(18,16)->(17,15)->(16,15)->(15,15)->(14,14)->(13,13)->(12,12)->(11,11)->(10,10)->(9,9)->(8,8)->(7,7)->(6,6)->(5,5)->(4,4)->(3,3)->(2,2)->(1,1)->(0,0)->Tracebacking end.

    time(ms): 0.048
    GGGCCCATAGCTCAG--TGGTAGAGTGCCTCCTTTGCAAGGAGGATGCCCTGGGTTCGAATCCCAGTGGGTCCAT
    |||||||||||||||  ||| |||| ||| || |||||||| ||| |||| |||||| |||||| ||||||||||
    GGGCCCATAGCTCAGCCTGGGAGAGCGCCGCCCTTGCAAGGCGGAGGCCCCGGGTTCAAATCCCGGTGGGTCCAT
    scoring:  match = 1,  mismatch = -1, indel = -1
    matches: 64,  score: 53

Results are appended to `output.txt` as follows:

    $ cat out.txt
    2014 8/11 15:46:30
    GGGCCCATAGCTCAG--TGGTAGAGTGCCTCCTTTGCAAGGAGGATGCCCTGGGTTCGAATCCCAGTGGGTCCAT
    |||||||||||||||  ||| |||| ||| || |||||||| ||| |||| |||||| |||||| ||||||||||
    GGGCCCATAGCTCAGCCTGGGAGAGCGCCGCCCTTGCAAGGCGGAGGCCCCGGGTTCAAATCCCGGTGGGTCCAT
    scoring:  match = 1,  mismatch = -1, indel = -1
    matches: 64,  score: 53

    2014 8/11 16:26:2
    GGGCCCATAGCTCAGTGGTAGAGTGCCTCCTTTGCAAGGAGGATGCCCTGGGTTCGAATCCCAGTGGGTCCAT
    |||||||||||||        |  |   ||  ||   ||| || |  |   |  ||   |||  |   | |  
    GGGCCCATAGCTC--------A--G---CC--TG---GGA-GA-G--C---G-CCG---CCC--T---TGC--
    scoring:  match = 1,  mismatch = -1, indel = -1
    matches: 35,  score: -3

## Installation

    $ git clone git@github.com:kmiya/Needleman-Wunsch.git
    $ cd Needleman-Wunsch
    $ make
