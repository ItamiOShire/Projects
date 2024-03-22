import java.util.Scanner;

public class Blackjack {
    private final String player;
    private final int max_iter;
    private int player_score;
    private int comp_score;
    private Deck deck;

    public Blackjack(String name,int iter){
        this.player=name;
        this.max_iter=iter;
        this.deck=new Deck();
        this.player_score=0;
        this.comp_score=0;
    }

    public void play() {
        Scanner scanner = new Scanner(System.in);
        for (int i = 0; i <= max_iter; i++) {
            System.out.println("Opcje: PLAY, STOP, QUIT");
            String option = scanner.nextLine().toUpperCase();

            switch (option) {
                case "PLAY":
                    playRound();
                    break;
                case "STOP":
                    stopGame();
                    break;
                case "QUIT":
                    quitGame();
                    break;
                default:
                    System.out.println("Nie rozpoznano opcji. Spróbuj ponownie");
            }
        }
        stopGame();
    }

    private void playRound()
    {
        Card playerCard = deck.getCard();
        Card compPlayer=deck.getCard();

        if(playerCard !=null && compPlayer!=null){
            player_score+=playerCard.rank.getWeight();
            comp_score+=compPlayer.rank.getWeight();
            System.out.println(player + " drew: " + playerCard);
            System.out.println("Computer drew: " + compPlayer);
            System.out.println("Player score: " + player_score);
            System.out.println("Computer score: " + comp_score);
        }
        else {
            System.out.println("Skończyły się karty");
            stopGame();
        }
    }
    private void stopGame(){
        System.out.println("Gra skończona!");
        System.out.println("Wyniki:");
        System.out.println(player + ": "+player_score+", Computer: "+comp_score);
        if(Math.abs(21-player_score) < Math.abs(21-comp_score)){
            System.out.println(player + " wins!");
        } else if (Math.abs(21-player_score) > Math.abs(21-comp_score)){
            System.out.println("Computer wins!");
        } else {
            System.out.println("It's a tie!");
        }
    }
    private void quitGame() {
        System.out.println("Quitting the game.");
        System.exit(0);
    }
}
