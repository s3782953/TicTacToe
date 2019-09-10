import java.util.Scanner;

public class TicTacToe {
    private static int row = 3; // The Row Length
    private static int column = 3; // The Column Height
    private static int[][] plane = new int[row][column]; // The main array
    private static int[][] marker = new int[row][column]; // The copy array
    private static int[][] filler = new int[row][column];
    private static boolean finish = true; // Checks if all the spaces are filled
    private static boolean flick = false; // Flicks true once the computer made a move
    private static boolean tick = false;
    private static boolean another = false;
    private static boolean win = false;

    public static void main(String[] args) { // The main method
        while (finish) { // Runs until the finish variable is flase
            player(); // The players move
            complete(); // Checks if all spaces are filled
            Check();
            algorithm(); // The computers move
            status(); // Prints out the status of the game
            win();
        }
    }

    private static void player() { // The players method which ask you simple 'Which location do you like to make
                                   // your move?''
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter your move...");
        System.out.println("Enter Width:");
        int user_row = scan.nextInt();
        System.out.println("Enter Length");
        int user_col = scan.nextInt();
        plane[user_row - 1][user_col - 1] = 1;
    }

    private static void algorithm() { // The computers algorithm
        while (flick == false && finish == true && tick == false) {
            int newrow = 0;
            int newcol = 0;
            double random = Math.round(Math.random() * 8); // Chooses a number bewtween 0-8 (since arrays starts at 0)
            System.out.println(random);
            for (int i = 0; i < random; i++) {
                newcol++;
                if (newcol > 2) {
                    newrow++;
                    newcol = 0;
                }
            }
            if (plane[newrow][newcol] != 2 && plane[newrow][newcol] != 1 && flick == false) {
                plane[newrow][newcol] = 2;
                flick = true;
            }
        }
        clear();
        flick = false;
        tick = false;
    }

    private static void Check() { // Checks if there are any nearby wins
        int counter = 0;
        int xcounter = 0;
        boolean again = true;
        row();
        col();
        dwnDiag();
        upDiag();

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (marker[i][j] == 1) {
                    counter++;
                    another = true;
                }
            }
        }
        while (again == true && another == true) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    if (marker[i][j] == 1 && again == true) {
                        double random = Math.round(Math.random() * (counter - 1) + 1);
                        xcounter++;
                        if (random == xcounter) {
                            plane[i][j] = 2;
                            tick = true;
                            again = false;
                        }
                    }
                }
            }
            xcounter = 0;
        }
    }

    private static void complete() { // Checks if the game is finish once all spaces are filled out
        int counter = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (plane[i][j] == 0) {
                    counter++;
                }
            }
        }
        if (counter == 0) {
            finish = false;
        }

    }

    private static void status() { // Prints out the status of the game
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                System.out.print("Row " + (i + 1) + ":  Column " + (j + 1) + " : ");
                System.out.println(plane[i][j]);
            }
        }
    }

    private static void win() { //Checks if player has won
        if (win == true) {
            finish = false;
            System.out.println("PLAYER WINS");
        }
        
    }

    private static void row() { //Checks all rows for any nearby wins
        int counter = 0;
        int nrow = 0;
        int ncol = 0;
        int i = 0;
        int j = 0;
        boolean done = true;
        for (i = 0; i < row; i++) {
            for (j = 0; j < column; j++) {
                if (plane[i][j] == 1) {
                    counter++;
                }
                if (plane[i][j] == 0) {
                    nrow = i;
                    ncol = j;
                }
                if (plane[i][j] == 2) {
                    done = false;
                }
            }
            if (done == true && counter > 1) {
                marker[nrow][ncol] = 1;
            }
            if (counter > 2) {
                win = true;
            }
            counter = 0;
            done = true;
        }
    }

    private static void col() { //Checks all columns for nearby wins
        int counter = 0;
        int nrow = 0;
        int ncol = 0;
        int i = 0;
        int j = 0;
        boolean done = true;
        for (j = 0; j < row; j++) {
            for (i = 0; i < column; i++) {
                if (plane[i][j] == 1) {
                    counter++;
                }
                if (plane[i][j] == 0) {
                    nrow = i;
                    ncol = j;
                }
                if (plane[i][j] == 2) {
                    done = false;
                }
            }
            if (done == true && counter > 1) {
                marker[nrow][ncol] = 1;
            }
            if (counter > 2) {
                win = true;
            }
            counter = 0;
            done = true;
        }
    }

    private static void dwnDiag() { //Checks down diagnol for nearby wins
        int counter = 0;
        int tracker = 0;
        int nrow = 0;
        int ncol = 0;
        int i = 0;
        int j = 0;
        boolean done = true;
        
        while (tracker < row) {
            if (plane[i][j] == 1) {
                counter++;
            }
            if (plane[i][j] == 0) {
                nrow = i;
                ncol = j;
            }
            if (plane[i][j] == 2) {
                done = false;
            }
            i++;
            j++;
            tracker++;
        }
        if (done == true && counter > 1) {
            marker[nrow][ncol] = 1;
        }
        if (counter > 2) {
            win = true;
        }
    }

    private static void upDiag() { //Check up Diagnol for nearby wins
        int counter = 0;
        int tracker = 0;
        int nrow = 0;
        int ncol = 0;
        int i = 0;
        int j = 2;
        boolean done = true;

        while (tracker < row) {
            if (plane[i][j] == 1) {
                counter++;
            }
            if (plane[i][j] == 0) {
                nrow = i;
                ncol = j;
            }
            if (plane[i][j] == 2) {
                done = false;
            }
            i++;
            j--;
            tracker++;
        }
        if (done == true && counter > 1) {
            marker[nrow][ncol] = 1;
        }
        if (counter > 2) {
            win = true;
        }
    }

    private static void clear() { //Clears markers
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                marker[i][j] = 0;
            }
        }
        another = false;
    }

}