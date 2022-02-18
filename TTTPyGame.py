import  pygame, sys
import numpy as np

#pygame coordinates start in the top left corner

pygame.init()

WIDTH = 600

SQUARE_SIZE = 200

HEIGHT = 600

SCREEN_COLOUR = (100, 0, 170)

TEAL_LINE = (0, 128, 128)

LIME_GREEN = (50,205,50)

CROSS_PINK = (255,105, 180)
CROSS_WIDTH = 25
SPACE_BETWEEN_LC = 55

CIRCLE_RADIUS = 60
CIRCLE_WIDTH = 15


LINE_WIDTH = 15

BOARD_ROWS = 3
BOARD_COLS = 3

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption( "Tic Tac Toe")
screen.fill(SCREEN_COLOUR)

#creating the board
playas_corner = np.zeros( (BOARD_ROWS, BOARD_COLS))
print(playas_corner)



#line drawing takes these arguments (where is going, colour, starting point, ending point, width)

#pygame.draw.line(screen, TEAL_LINE, (100,200), (500,200), LINE_WIDTH)

#create a function to draw the lines of the grid
def draw_lines():
    
    pygame.draw.line(screen, TEAL_LINE, (50,200), (550,200), LINE_WIDTH)
    pygame.draw.line(screen, TEAL_LINE, (50,400), (550,400), LINE_WIDTH)
    pygame.draw.line(screen, TEAL_LINE, (200,50), (200,550), LINE_WIDTH)
    pygame.draw.line(screen, TEAL_LINE, (400,50), (400,550), LINE_WIDTH)
    
def draw_figures():
    for row in range (BOARD_ROWS):
        for col in range (BOARD_COLS):
          if playas_corner[row][col] == 1:
              pygame.draw.circle(screen, LIME_GREEN, (int(col * 200 + 100), int(row * 200 +100)), CIRCLE_RADIUS, CIRCLE_WIDTH)
          elif playas_corner [row][col] == 2:
              
            pygame.draw.line( screen, CROSS_PINK, (col * SQUARE_SIZE + SPACE_BETWEEN_LC, row * SQUARE_SIZE + SQUARE_SIZE - SPACE_BETWEEN_LC), (col * SQUARE_SIZE + SQUARE_SIZE - SPACE_BETWEEN_LC, row * SQUARE_SIZE + SPACE_BETWEEN_LC), CROSS_WIDTH )	
            pygame.draw.line( screen, CROSS_PINK, (col * SQUARE_SIZE + SPACE_BETWEEN_LC, row * SQUARE_SIZE + SPACE_BETWEEN_LC), (col * SQUARE_SIZE + SQUARE_SIZE - SPACE_BETWEEN_LC, row * SQUARE_SIZE + SQUARE_SIZE - SPACE_BETWEEN_LC), CROSS_WIDTH )
        
               

def mark_square(row, col, playa):
    playas_corner[row][col] = playa
    
def available(row, col):
    if playas_corner[row][col] == 0:
        return True
    else:
        return False
    
def is_board_full():
    for row in range(BOARD_ROWS):
        for col in range(BOARD_COLS):
            if playas_corner[row][col] == 0:
                return False
    return True

def check_if_won (playa):
    # vertical check
    board = playas_corner
    for i in range (BOARD_COLS):
        if board [0][i] == playa and board[1][i] == playa and board [2][i] == playa:
            draw_vert_win( i, playa)
            return True
    #horizontal check
    for i in range(BOARD_ROWS):
        if board [i][0] == playa and board[i][1] == playa and board [i][2] == playa:
            draw_horz_win(i, playa)
            return True
            
    # diagonal checks
    if board [2][0] == playa and board [1][1] == playa and board [0][2] == playa:
         draw_diag_win(1, playa)
         return True
        
    if board[0][0] == playa and board [1][1] == playa and board [2][2] == playa:
        draw_diag_win(2, playa)
        return True
         
        
    pass

def draw_vert_win(col, playa):
    x_coordinate = (col * 200) + 100
    if playa == 1:
        color = LIME_GREEN
    elif playa == 2:
        color = CROSS_PINK
        
    pygame.draw.line(screen, color, (x_coordinate, 15), (x_coordinate, HEIGHT-15), LINE_WIDTH)
                

def draw_horz_win(row, playa):
    
    y_coordinate = (row * 200) + 100
    
    if playa == 1:
        color = LIME_GREEN
    elif playa == 2:
        color = CROSS_PINK
    
    pygame.draw.line(screen, color, (15, y_coordinate,), (WIDTH - 15, y_coordinate), LINE_WIDTH)
    

def draw_diag_win(direction, playa):
    if playa == 1:
        color = LIME_GREEN
    elif playa == 2:
        color = CROSS_PINK
    
    if direction == 1:
        pygame.draw.line(screen, color, (15, HEIGHT-15), (WIDTH - 15, 15), 15)
        
    elif direction == 2:
        pygame.draw.line(screen, color, (15,15), (WIDTH-15 , HEIGHT-15), 15)

def restart():
    screen.fill(SCREEN_COLOUR)
    draw_lines()
    player = 1
    game_over = False
    for row in range (BOARD_ROWS):
        for col in range (BOARD_COLS):
            playas_corner[row][col] = 0
    
    
#print (is_board_full())
#for row in range(BOARD_ROWS):
#        for col in range(BOARD_COLS):
#            mark_square (row,col,1)
    
#print(is_board_full())

#mark_square(1,1,1)

#print(playas_corner)
#print(available(1,1))

draw_lines()


player = 1

game_over = False

#main loop
running = True
while running:
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
            
        if event.type == pygame.MOUSEBUTTONDOWN and not game_over:
            
            mousex = event.pos[0]
            mousey= event.pos[1]
            
            clicked_row = int(mousey // 200)
            clicked_col = int(mousex // 200)
            
            print(clicked_row)
            print(clicked_col)
            
            if available(clicked_row, clicked_col):
                if player == 1:
                    mark_square(clicked_row, clicked_col, 1)
                    if check_if_won(player):
                        game_over = True
                    player = 2
                    
                elif player == 2:
                    mark_square(clicked_row, clicked_col, 2)
                    if check_if_won(player):
                        game_over = True
                    player = 1
                    
                draw_figures()
                
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_r:
                restart()
        
                    
                #print(playas_corner)
                
                    
                
                
    pygame.display.update()
            
            
    