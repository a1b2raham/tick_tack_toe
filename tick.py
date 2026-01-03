game = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
comp = {}
over = False


def print_tick(game):
    print("  0 1 2")
    for i in range(3):
        print(i, end="")
        print("|", end="")
        for j in range(3):
            if game[i][j] == 0:
                print(" ", end="")
            elif game[i][j] == -1:
                print("X", end="")
            elif game[i][j] == 1:
                print("O", end="")
            print("|", end="")
        print()


def chk_win(game):
    for i in range(3):
        if game[i][0] == game[i][1] == game[i][2] != 0:
            return game[i][0]
        if game[0][i] == game[1][i] == game[2][i] != 0:
            return game[0][i]
    if game[0][0] == game[1][1] == game[2][2] != 0:
        return game[0][0]
    if game[0][2] == game[1][1] == game[2][0] != 0:
        return game[0][2]
    return 0


def find_open(game):
    open = []
    for i in range(3):
        for j in range(3):
            if game[i][j] == 0:
                open.append((i, j))
    return open


def minmax(game, maxp, depth, result):
    chk = chk_win(game)
    if chk == 1:
        return 10 - depth
    elif chk == -1:
        return -10 + depth

    open = find_open(game)
    if len(open) == 0:
        return 0

    if maxp:
        max_score = -10
        for i in open:
            x, y = i
            game[x][y] = 1
            a = minmax(game, False, depth + 1, result)
            max_score = max(a, max_score)
            if depth == 1:
                result[(x, y)] = a
            game[x][y] = 0
        return max_score
    else:
        min_score = 10
        for i in open:
            x, y = i
            game[x][y] = -1
            score = minmax(game, True, depth + 1, result)
            min_score = min(score, min_score)
            game[x][y] = 0
        return min_score


def tick():
    open = find_open(game)
    print("Welcome to the Tic-Tac-Toe Game!/n")
    while True:
        print_tick(game)
        inp = input("Enter the position to place your mark in the format row-column: ")
        x, y = inp.split("-")
        x = int(x)
        y = int(y)
        if (x, y) in open:
            open.remove((x, y))
            game[x][y] = -1
        else:
            print("Invalid Move")
            continue
        chk = chk_win(game)
        if chk == 1:
            print("You Lost!")
            break
        elif chk == -1:
            print("You Win!")
            break
        elif len(open) == 0:
            print("It's a Tie!")
            break
        result = {}
        minmax(game, True, 1, result)

        x, y = sorted(result.keys(), key=lambda x: result[x], reverse=True)[0]
        game[x][y] = 1
        open.remove((x, y))
        chk = chk_win(game)
        if chk == 1:
            print("You Lost!")
            break
        elif chk == -1:
            print("You Win!")
            break
        elif len(open) == 0:
            print("It's a Tie!")
            break


tick()
