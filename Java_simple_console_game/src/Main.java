import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Random;

class OptionNotRecognizedException extends IllegalArgumentException
{
    OptionNotRecognizedException(String message)
    {
        super(message);
    }
}



interface CheckStep {
    boolean check(char[][] board, int i0, int j0, Direction direction);
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int size = 0;
        while (size < 2) {
            try {
                System.out.println("Podaj wysokość planszy:");
                size = sc.nextInt();
                if (size < 2) {
                    throw new InputMismatchException();
                }
            } catch (InputMismatchException e) {
                System.out.println("BŁĄD: Podaj jeszcze raz! (minimalny rozmiar planszy to 2)");
                sc.nextLine();
            }
        }

        char[][] board = Board.generateBoard(size);

        int playerX = new Random().nextInt(2 * size);
        int playerY = new Random().nextInt(size);
        board[playerX][playerY] = 'o';

        while (true) {
            Board.printBoard(board);

            System.out.println("Podaj ruch (l - LEFT, r - RIGHT, u - UP, d - DOWN, q - QUIT):");
            String userInput = sc.next();

            try {
                int[] newPlayerPosition = Board.processMove(userInput, board, playerX, playerY, (b, i, j, d) ->
                        i + d.getX() >= 0 && i + d.getX() < b.length &&
                                j + d.getY() >= 0 && j + d.getY() < b[0].length &&
                                b[i + d.getX()][j + d.getY()] != 'X'
                );

                if (userInput.equals("q")) {
                    System.out.println("Gra zakończona.");
                    break;
                }

                playerX = newPlayerPosition[0];
                playerY = newPlayerPosition[1];
            } catch (OptionNotRecognizedException e) {
                System.out.println("BŁĄD: " + e.getMessage());
            }
        }

        sc.close();
    }
}
