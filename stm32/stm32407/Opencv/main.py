import sensor, image, time , pyb
import struct
from pyb import UART
from pyb import Pin
from pyb import LED
Base_threshold = (49, 78, 0, 51, -4, 46)
W_threshold = (79, 98, 70, -65, 80, -80)
B_threshold = (47, 20, 10, -22, 90, -40)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
clock = time.clock()
send_flag = 0
uart = UART(3, 115200, timeout_char=1000)
pin3 = Pin('P3', Pin.IN, Pin.PULL_UP)
pin6 = Pin('P6', Pin.IN, Pin.PULL_UP)
pin7 = Pin('P7', Pin.OUT_PP, Pin.PULL_NONE)
pin8 = Pin('P8', Pin.OUT_PP, Pin.PULL_NONE)
first_identify = True
corner_accum = [(0,0)] * 9
count = 0
sorted_points = [(0,0)] * 9
vul_points = [0]* 9
fine_sccess = 1
HUMAN = -1
COMP = +1
debug = False
Mode = 4
Mode_num = 0
YOVER = 0
board = [
     [" "," "," "],
     [" "," "," "],
     [" "," "," "],
]
mode = 0
def outuart(x, a, f_x , f_a):
    global uart
    data = bytearray(
            [0x2C, 0x12, int(x), int(a), int(f_x), int(f_a), 0x5B]
        )
    uart.write(data);
def rotate_move(move):
    if(move == 1):
        return 7
    elif(move == 2):
        return 4
    elif(move == 3):
        return 1
    elif(move == 4):
        return 8
    elif(move == 5):
        return 5
    elif(move == 6):
        return 2
    elif(move == 7):
        return 9
    elif(move == 8):
        return 6
    elif(move == 9):
        return 3
    else :return
def pause_uart_data(data,sorted_points):
    if(data == 1):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag =  1
    elif(data == 2):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag = 1
    elif(data == 3):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag = 1
    elif(data == 4):
         for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
         send_flag = 1
    elif(data == 5):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag = 1
    elif(data == 6):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag = 1
    elif(data == 7):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag = 1
    elif(data == 8):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag = 1
    elif(data == 9):
        for i in range(4):
            print(sorted_points[data-1][0],sorted_points[data-1][1])
            outuart(sorted_points[data-1][0],sorted_points[data-1][1],0,0)
        send_flag = 1;
    else:
        return
board = [
     [" "," "," "],
     [" "," "," "],
     [" "," "," "],
]
SIZE = 3
def check_win(board, player):
    for i in range(SIZE):
        if all(board[i][j] == player for j in range(SIZE)) or \
           all(board[j][i] == player for j in range(SIZE)):
            return True
    if all(board[i][i] == player for i in range(SIZE)) or \
       all(board[i][SIZE - 1 - i] == player for i in range(SIZE)):
        return True
    return False
def check_draw(board):
    return all(board[i][j] != ' ' for i in range(SIZE) for j in range(SIZE))
def minimax(board, depth, is_maximizing):
    computer = 'X'
    player = 'O'
    if check_win(board, computer):
        return 10 - depth
    if check_win(board, player):
        return depth - 10
    if check_draw(board):
        return 0
    if is_maximizing:
        best_score = float('-inf')
        for i in range(SIZE):
            for j in range(SIZE):
                if board[i][j] == ' ':
                    board[i][j] = computer
                    score = minimax(board, depth + 1, False)
                    board[i][j] = ' '
                    best_score = max(score, best_score)
        return best_score
    else:
        best_score = float('inf')
        for i in range(SIZE):
            for j in range(SIZE):
                if board[i][j] == ' ':
                    board[i][j] = player
                    score = minimax(board, depth + 1, True)
                    board[i][j] = ' '
                    best_score = min(score, best_score)
        return best_score
def computer_move(board):
    if board == [
        [" "," "," "],
        [" "," "," "],
        [" "," "," "]
    ]:
        return 1,1
    best_score = float('-inf')
    move = (-1, -1)
    for i in range(SIZE):
        for j in range(SIZE):
            if board[i][j] == ' ':
                board[i][j] = 'X'
                score = minimax(board, 0, False)
                board[i][j] = ' '
                if score > best_score:
                    best_score = score
                    move = (i, j)
    if move != (-1, -1):
        return move[0], move[1]
def check_turn(board):
    x_count = sum(row.count("X") for row in board)
    o_count = sum(row.count("O") for row in board)
    return "X" if x_count == o_count else "O"
def convert_to_char(value):
    if value == 1:
        return "O"
    elif value == 2:
        return "X"
    else:
        return " "
def sort_points(points):
    points = sorted(points, key=lambda p: p[1])
    rows = [points[i:i+3] for i in range(0, len(points), 3)]
    sorted_points = [sorted(row, key=lambda p: p[0]) for row in rows]
    sorted_points = [point for row in sorted_points for point in row]
    return sorted_points
def saomiao(img_re,img):
    if debug:
        print('test point--------------5-----在每一个小棋盘中识别棋子')
    for i in range(9):
        _blobs = img_re.find_blobs([W_threshold,B_threshold],
                                    roi = (sorted_points[i][0]-35,sorted_points[i][1]-35,70,70),
                                    pixels_threshold=800, area_threshold=800)
        if _blobs == [] :
            if debug:
                pass
            vul_points[i] = 0
        for blob in _blobs:
            if blob.w() > 55 and blob.h() > 55:
                continue
            if blob.w() < 20 and blob.h() < 20:
                continue
            aspect_ratio = blob.w() / blob.h()
            if aspect_ratio < 0.6 or aspect_ratio > 1.4:
                continue
            if blob.code() == 1:
                enclosing_circle = blob.enclosing_circle()
                img.draw_circle(enclosing_circle[0], enclosing_circle[1], enclosing_circle[2], color=(0, 255, 0))
                if debug:
                    pass
                vul_points[i] = 1
            elif blob.code() == 2:
                enclosing_circle = blob.enclosing_circle()
                img.draw_circle(enclosing_circle[0], enclosing_circle[1], enclosing_circle[2], color=(0, 0, 255))
                if debug:
                    print('test point--------------6-----%d 为黑'%(i+1))
                vul_points[i] = 2
    return img
while(True):
    clock.tick()
    data_uart = uart.read()
    if data_uart != None :
        print('test point--------------1-----读取串口数据接收指令为%s' % data_uart)
        if(data_uart == b'\x01'):
            YOVER = 1
    img = sensor.snapshot()
    img_re = img
    img_re2 = img
    if(pin3.value()==0):
        fine_sccess = 1
        send_flag = 0
        outuart(0,0,0,5)
        print("重置中心坐标点位！")
    else:
        fine_sccess = 0
    if(pin6.value() == 0):
        time.sleep_ms(70)
        if(pin6.value() == 0):
            Mode_num += 1
    if(Mode_num == 1):
        pin7.value(1)
        pin8.value(0)
        Mode = 4
    elif(Mode_num ==2):
        pin8.value(1)
        pin7.value(0)
        Mode = 5
    elif(Mode_num>=3):
        pin7.value(0)
        pin8.value(0)
        Mode_num = 0
    while fine_sccess == 1:
        LED(3).on()
        if debug:
            print('test point--------------2-----寻找是否为9个')
        imgfind = sensor.snapshot()
        Base_blobs = imgfind.find_blobs([Base_threshold],roi=(10,10,300,220), pixels_threshold=800, area_threshold=800)
        find_count = 0
        for blob in Base_blobs:
            corners = blob.min_corners()
            if blob.w() > 100 and blob.h() > 100:
                continue
            if blob.w() < 20 and blob.h() < 20:
                continue
            img.draw_cross(blob.cx(), blob.cy(),
                           size=2, color=(255, 0, 0))
            corner_accum[find_count]= (blob.cx(), blob.cy())
            for i in range(4):
                img.draw_line(corners[i][0], corners[i][1], corners[(i + 1) % 4][0], corners[(i + 1) % 4][1],color=(255, 0, 0))
            find_count += 1
            if debug:
                pass
        if  find_count == 9:
            if debug:
                pass
            sorted_points = sort_points(corner_accum)
            break
        else:
            if debug:
                pass
            corner_accum = [(0,0)] * 9
            continue
    fine_sccess = 0
    LED(3).off()
    if(send_flag == 0):
        outuart(0,0,0,5)
    send_flag = 1;
    if debug:
        pass
    for i in range(9):
        img.draw_cross(sorted_points[i][0], sorted_points[i][1],
                       size=2, color=(255, 0, 255))
        img.draw_string(sorted_points[i][0], sorted_points[i][1], '%d' % (i+1), color=(255, 0, 255),scale = 2)
    if(Mode  == 4):
        if(YOVER == 1):
            LED(3).on()
            time.sleep(8)
            print("白棋已经下了")
            LED(3).off()
            for i in range(100):
                img = saomiao(img_re,img)
            initial_state = vul_points
            converted_state = [convert_to_char(value) for value in initial_state]
            board = [converted_state[i:i + 3] for i in range(0, len(converted_state), 3)]
            print(board)
            if check_win(board, 'O'):
                print("你赢啦!")
                outuart(0,0,1,0)
                Mode = 0
            elif check_win(board, 'X'):
                print("我赢啦！")
                outuart(0,0,1,0)
                Mode = 0
            elif check_draw(board):
                print("平局啦！")
                outuart(0,0,1,0)
                Mode = 0
            elif check_turn(board) == "X":
                line,row = computer_move(board)
                print('test point--------------mode4-----下棋的坐标为')
                print(line)
                print(row)
                move_index = line*3 + (row+1)
                move_index= rotate_move(move_index)
                print('test point--------------mode4-----运行完成-落点为:%d' %move_index)
                outuart(0,0,0,move_index)
            elif check_turn(board) == "O":
                print("该你下了！")
            YOVER = 0
    elif(Mode  == 5):

        if(YOVER == 1):
            LED(3).on()
            time.sleep(5)
            print("白棋已经下了")
            LED(3).off()
            for i in range(100):
                img = saomiao(img_re,img)
            initial_state = vul_points
            converted_state = [convert_to_char(value) for value in initial_state]
            board = [converted_state[i:i + 3] for i in range(0, len(converted_state), 3)]
            if check_win(board, 'X'):
                print("我赢啦!")
                Mode = 0
            elif check_win(board, 'O'):
                print("你赢啦！")
                Mode = 0
            elif check_draw(board):
                print("平局啦！")
                Mode = 0
            elif check_turn(board) == "O":
                line,row = computer_move(board)
                print('test point--------------mode5-----下棋的坐标为')
                print(line)
                print(row)
                move_index = line*3 + (row+1)
                move_index= rotate_move(move_index)
                print('test point--------------mode5-----运行完成-落点为:%d' %move_index)
                outuart(0,0,0,move_index)
            elif check_turn(board) == "X":
                uart.write('AAY')
                print("该你下了！")
            YOVER = 0
