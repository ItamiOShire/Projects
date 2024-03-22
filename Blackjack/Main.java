// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        Blackjack blackjackGame = new Blackjack("Player", 10);
        System.out.println(Card.Rank.values());
        blackjackGame.play();
    }
}