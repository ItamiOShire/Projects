import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.security.InvalidParameterException;
import java.util.Arrays;
import static org.junit.jupiter.api.Assertions.*;

class BigNumberTest
{
    private byte[] integer;
    private byte[] frac;
    private BigNumber ob;

    @BeforeEach
    void setUp()
    {
        integer = new byte[] {1,2,3};
        frac = new byte[] {1,2,3};
        ob = new BigNumber(integer,frac);
    }

    @Test
    void constructor()
    {
        assertThrows(NullPointerException.class, () -> new BigNumber(null,null));
        assertThrows(NullPointerException.class, () -> new BigNumber(integer,null));
        assertThrows(NullPointerException.class, () -> new BigNumber(null,frac));
        assertDoesNotThrow(() -> new BigNumber(new byte[]{0},new byte[]{0}));
        assertThrows(InvalidParameterException.class,() -> new BigNumber(new byte[]{},new byte[]{}));
        assertThrows(InvalidParameterException.class,() -> new BigNumber(new byte[]{},frac));
        assertThrows(InvalidParameterException.class,() -> new BigNumber(integer,new byte[]{}));
        //assertThrows(InvalidParameterException.class,() -> new BigNumber(new byte[]{0,1},frac));
        assertThrows(InvalidParameterException.class,() -> new BigNumber(new byte[]{'a','b',1},frac));
        assertThrows(InvalidParameterException.class,() -> new BigNumber(integer,new byte[]{'a','b',1}));


        //Testowanie metody toString()
        //dane testowe 1
        String test="123.123";
        assertEquals(test,ob.toString());

        //dane testowe 2
        integer[0]++;
        frac[1]++;

        //spelnia zasade niezmiennosci klasy
        assertNotEquals(new BigNumber(integer,frac),ob);

        test = "223.133";
        ob=new BigNumber(integer,frac);
        assertEquals(test,ob.toString());

        //dane testowe 3
        integer=new byte[]{0};
        frac=new byte[]{0};
        test="0.0";
        ob=new BigNumber(integer,frac);
        assertEquals(test,ob.toString());


    }

    @Test
    void valueOf()
    {
        assertThrows(NullPointerException.class, () -> BigNumber.valueOf(integer,null));
        assertThrows(NullPointerException.class, () -> BigNumber.valueOf(null,frac));
        assertThrows(NullPointerException.class, () -> new BigNumber(null,null));

        assertThrows(InvalidParameterException.class,() -> BigNumber.valueOf(new byte[]{},new byte[]{}));
        assertThrows(InvalidParameterException.class,() -> BigNumber.valueOf(new byte[]{},frac));
        assertThrows(InvalidParameterException.class,() -> BigNumber.valueOf(integer,new byte[]{}));
        assertThrows(InvalidParameterException.class,() -> BigNumber.valueOf(new byte[]{0,1},frac));
        assertThrows(InvalidParameterException.class,() -> BigNumber.valueOf(new byte[]{'a','b',1},frac));
        assertThrows(InvalidParameterException.class,() -> BigNumber.valueOf(integer,new byte[]{'a','b',1}));

        assertEquals(ob,BigNumber.valueOf(integer,frac));

        integer=new byte[]{0};
        frac=new byte[]{0};
        assertEquals(BigNumber.ZERO , BigNumber.valueOf(integer,frac));
        assertSame(BigNumber.ZERO , BigNumber.valueOf(integer,frac));

        integer=new byte[]{1};
        assertEquals(BigNumber.ONE , BigNumber.valueOf(integer,frac));
        assertSame(BigNumber.ONE , BigNumber.valueOf(integer,frac));

        integer=new byte[]{2};
        assertEquals(BigNumber.TWO , BigNumber.valueOf(integer,frac));
        assertSame(BigNumber.TWO , BigNumber.valueOf(integer,frac));

        integer=new byte[]{1,0};
        assertEquals(BigNumber.TEN , BigNumber.valueOf(integer,frac));
        assertSame(BigNumber.TEN , BigNumber.valueOf(integer,frac));

        integer = new byte[]{0};
        frac=new byte[]{0,1};
        //zwraca niepoprawne dane w przypadku zwracania nowego obiektu- frac jest zamieniony z integer
        //assertEquals(new BigNumber(integer,frac) , BigNumber.valueOf(integer,frac));


    }
    @Test
    void getInteger()
    {
        assertArrayEquals(integer,ob.getInteger());
        assertNotSame(integer,ob.getInteger());
        byte[] test=ob.getInteger();
        test[0]++;
        //nie spelnia zasady niezmiennosci klasy
        //assertNotEquals(test,ob.getInteger());
    }

    @Test
    void getFrac()
    {
        //zwraca niepoprawna dlugosc tablicy
        //assertArrayEquals(frac,ob.getFrac());
        assertNotSame(frac,ob.getFrac());
        byte[] test=ob.getFrac();
        test[0]++;
        //spelnia zasade niezmiennosci klasy
        assertNotEquals(test,ob.getFrac());
    }

    @Test
    void floor()
    {
        if(BigNumber.areIntegerArraysSame(ob,ob.floor()))
        {
            System.out.println("Obiekt zwrócono poprawnie");
            ob = new BigNumber(integer, new byte[]{0});
            //zwraca niepoprawne dane
            //assertEquals(ob.toString(),ob.floor().toString());
        }
        else
            System.out.println("Obiekt nie zwrócono poprawnie");

    }

    @Test
    void equals()
    {
        BigNumber ob2 = new BigNumber(integer,frac);
        BigNumber ob3 = new BigNumber(integer,frac);
        assertTrue(ob.equals(ob2));
        assertTrue(ob2.equals(ob));
        assertFalse(ob.equals(null));
        assertTrue(ob2.equals(ob3));
        assertTrue(ob.equals(ob3));
        byte [] t=ob2.getInteger();
        t[0]++;
        assertFalse(ob.equals(ob2));
        String test="test";
        //funkcja equals nie zwraca falszu gdy obiekty są różnych klas
        //assertFalse(ob.equals(test));

    }

    @Test
    void hCode()
    {
        BigNumber ob2 = new BigNumber(integer,frac);
        assertEquals(ob,ob2);
        int hCodeOb=ob.hashCode();
        int hCodeOb2 = ob2.hashCode();
        assertEquals(hCodeOb,hCodeOb2);
        byte [] integer2=ob.getInteger();
        integer2[0]++;
        assertNotEquals(ob,ob2);
        //po zmienieniu pola integer (co nie powinno miec miejsca) obiektu ob funkcja zwraca ta sama wartosc hashCode
        //assertNotEquals(hCodeOb,hCodeOb2);
    }
}