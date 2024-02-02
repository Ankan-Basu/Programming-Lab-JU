cnt = 0

def edit_dist(str1, str2, str1_indx, str2_indx):
    global cnt
    cnt += 1
    '''
    Convert str1 to str2
    '''
    if (str1_indx < 0):
        # add remaining chars of str2 to str1 to make them equal
        # no of insertions = no of chars left in str2 = str2_indx + 1
        return str2_indx + 1

    if (str2_indx < 0):
        # delete remaining chars of str1 to make str1 == str2
        # no of deletions = no of chars left in str1 = str1_indx + 1
        return str1_indx + 1

    if (str1[str1_indx] == str2[str2_indx]):
        # no new operations. just move one indx back
        return edit_dist(str1, str2, str1_indx-1, str2_indx-1)
    else:
        # +1 for 1 operation

        #replace
        ## replace char at str1_indx (then str1[str1_indx] == str2[str2_indx])
        ## move back one indx now
        replace = 1 + edit_dist(str1, str2, str1_indx-1, str2_indx-1)

        #insert
        ## insert after str_indx1. (then str1[str1_indx+1] == str2[str2_indx])
        ## move back one indx now
        insert = 1 + edit_dist(str1, str2, str1_indx, str2_indx-1)

        #delete
        ## delete at str_indx1. pointer moves to str1_indx-1.
        ## stay at str2_indx and compare with str1_indx-1
        delete = 1 + edit_dist(str1, str2, str1_indx-1, str2_indx)

        return min(replace, insert, delete)


def edit_dist_memo(str1, str2, str1_indx, str2_indx, memo):
    global cnt
    cnt += 1
    '''
    Convert str1 to str2
    '''
    if (str1_indx < 0):
        # add remaining chars of str2 to str1 to make them equal
        # no of insertions = no of chars left in str2 = str2_indx + 1
        return str2_indx + 1

    if (str2_indx < 0):
        # delete remaining chars of str1 to make str1 == str2
        # no of deletions = no of chars left in str1 = str1_indx + 1
        return str1_indx + 1

    if (memo[str2_indx][str1_indx] != -1):
        return memo[str2_indx][str1_indx]
    else:
        if (str1[str1_indx] == str2[str2_indx]):
            # no new operations. just move one indx back
            memo[str2_indx][str1_indx] = edit_dist_memo(str1, str2, str1_indx-1, str2_indx-1, memo)
            return memo[str2_indx][str1_indx]
        else:
            # +1 for 1 operation

            #replace
            ## replace char at str1_indx (then str1[str1_indx] == str2[str2_indx])
            ## move back one indx now
            replace = 1 + edit_dist_memo(str1, str2, str1_indx-1, str2_indx-1, memo)

            #insert
            ## insert after str_indx1. (then str1[str1_indx+1] == str2[str2_indx])
            ## move back one indx now
            insert = 1 + edit_dist_memo(str1, str2, str1_indx, str2_indx-1, memo)

            #delete
            ## delete at str_indx1. pointer moves to str1_indx-1.
            ## stay at str2_indx and compare with str1_indx-1
            delete = 1 + edit_dist_memo(str1, str2, str1_indx-1, str2_indx, memo)

            memo[str2_indx][str1_indx] = min(replace, insert, delete)
            return memo[str2_indx][str1_indx]


if __name__ == '__main__':
    str1 = 'horse'
    str2 = 'ros'

    # global cnt

    memo = [[-1 for i in range(len(str1))] for i in range(len(str2))]

    res = edit_dist(str1, str2, len(str1)-1, len(str2)-1)
    print(f'{str1} -> {str2}: Edit Dist = {res}')
    print(f'Cnt: {cnt}')
    cnt = 0
    res = edit_dist_memo(str1, str2, len(str1)-1, len(str2)-1, memo)
    print(f'{str1} -> {str2}: Edit Dist = {res}')
    print(f'Cnt: {cnt}')
    cnt = 0
