#Preston Young 43798917

import game_logic as Logic

class ColumnsGame:
    def __init__(self):
        self.running = True

    def run(self) -> None:
        '''
        Runs the user interface part of the game
        by asking for several inputs: the number of
        rows and columns, whether to begin the field
        empty, and what action the user wants to take.
        Each time, the board updated and the print method is called.
        '''
        self.num_rows = int(input())
        self.num_cols = int(input())
        self.begin_field = input()
        self.contents = []
        self.construct_contents()

        Game = Logic.ColumnsState(self.num_rows, self.num_cols, self.contents)
        self.game_board = Game.create_board()
        self.print_board()
        
        while self.running:
            action = input()
            
            if action.startswith('F') and not Game.faller_exists:
                self.game_board = Game.create_faller(action.split()[1:])
                self.print_board()

            elif action == '<' and Game.faller_exists:
                self.game_board = Game.move_left()
                self.print_board()

            elif action == '>' and Game.faller_exists:
                self.game_board = Game.move_right()
                self.print_board()

            elif action == 'R' and Game.faller_exists:
                self.game_board = Game.rotate_faller()
                self.print_board()

            elif action == 'Q':
                self.running = False

            elif action == '' and Game.faller_exists:
                self.game_board = Game.drop()
                self.print_board()

            elif action == '' and not Game.faller_exists:
                self.game_board = Game.freeze()
                self.print_board()
                
            else:
                self.print_board()

            if Game.is_game_over:
                print('GAME OVER')
                self.running = False


    def construct_contents(self):
        '''
        If the user specifies contents,
        this method checks for additional inputs
        and constructs a list of the desired contents.
        If the user specifies empty, an appropriate list
        is made with spaces.
        '''
        if self.begin_field == 'CONTENTS':
            for i in range(2):
                self.contents.append(list(' '*self.num_cols))
            
            for i in range(self.num_rows):
                self.contents.append(list(input()))

        else:
            for i in range(self.num_rows+2):
                self.contents.append(list(' '*self.num_cols))
                
            
    def print_board(self):
        '''
        Takes the current board and prints it.
        '''
        for row in self.game_board[2:]:
            for col in row:
                print(col, end = '')
            print()
        print(' ' + '---'*self.num_cols + ' ')

if __name__ == '__main__':
    ColumnsGame().run()
