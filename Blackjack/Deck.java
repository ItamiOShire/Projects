import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Deck {
    private List<Card> deck;

    Deck(){
        deck = new ArrayList<>();
        for(Card.Suit suit:Card.Suit.values()) {
            for(Card.Rank rank: Card.Rank.values()) {
                deck.add(new Card(suit,rank));
            }
        }
        Collections.shuffle(deck);
    }

    @Override
    public String toString() {
        return "Deck: "+deck;
    }
    public Card getCard()
    {
        if(!deck.isEmpty()) {
            return deck.remove(deck.size() - 1);
        }
        return null;
    }

    public void shuffleDeck()
    {
        Collections.shuffle(deck);
    }
}
