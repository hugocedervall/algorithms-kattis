def autori(seq):
    return_seq = ""
    seq_list = seq.split("-")
    for str in seq_list:
        if str:
            return_seq += str[0]
    return return_seq;


print(autori(input()))

