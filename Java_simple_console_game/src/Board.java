import java.util.Random;
public class Board {
    public static char[][] generateBoard(int size) {
        char[][] board = new char[2 * size][size];
        Random random = new Random();

        for (int i = 0; i < 2 * size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = (random.nextDouble() < 0.3) ? 'X' : ' ';
            }
        }

        return board;
    }

    public static void printBoard(char[][] board) {
        for (char[] row : board) {
            for (char cell : row) {
                System.out.print(cell + " ");
            }
            System.out.println();
        }
    }

    public static int[] processMove(String userInput, char[][] board, int playerX, int playerY, CheckStep checkStep) {
        Direction direction;

        switch (userInput) {
            case "l":
                direction = Direction.LEFT;
                break;
            case "r":
                direction = Direction.RIGHT;
                break;
            case "u":
                direction = Direction.UP;
                break;
            case "d":
                direction = Direction.DOWN;
                break;
            case "q":
                return new int[]{playerX, playerY};
            default:
                throw new OptionNotRecognizedException("Nieprawidłowa opcja.");
        }

        if (checkStep.check(board, playerX, playerY, direction)) {
            board[playerX][playerY] = ' ';
            playerX += direction.getX();
            playerY += direction.getY();
            board[playerX][playerY] = 'o';
        } else {
            throw new OptionNotRecognizedException("Nie można wykonać tego ruchu.");
        }

        return new int[]{playerX, playerY};
    }
}
