public final class Card {

    enum Suit{
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES;
    }
    enum Rank{
        NINE(9,"9"),
        TEN(10,"10"),
        JACK(2,"J"),
        QUEEN(3,"Q"),
        KING(4,"K"),
        ACE(1,"A");

        private final int weight;
        private final String symbol;

        Rank(int w, String s) {
            this.weight=w;
            this.symbol=s;
        }

        @Override
        public String toString() {
            return symbol;
        }
        public int getWeight()
        {
            return weight;
        }
        public String getSymbol()
        {
            return symbol;
        }
    }

    public final Suit suit;
    public final Rank rank;

    public Card(Suit suit,Rank rank) {
        this.rank=rank;
        this.suit=suit;
    }

    @Override
    public String toString(){
        return rank + " " + suit;
    }

}
