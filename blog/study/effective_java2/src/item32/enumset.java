package item32;

import java.util.EnumSet;
import java.util.Set;

public class enumset {
	
	public enum Color { RED, BLUE, GREEN };

	public static void main(String[] args) {
		Set<Color> s  = EnumSet.of(Color.RED, Color.BLUE);
		System.out.println(s);

	}

}
