import java.util.HashMap;
import java.util.Stack;

public class valid_parentheses {
    public static void main(String[] args) {
        assert is_valid_parentheses(""); // empty is valid
        assert is_valid_parentheses("*");
        assert is_valid_parentheses("()");
        assert is_valid_parentheses("{}");
        assert is_valid_parentheses("[]");
        assert is_valid_parentheses("{()}");
        assert is_valid_parentheses("([{}])");

        assert !is_valid_parentheses("([)]");
    }
    
    // It is a short program, and every word is important for its correctness
    public static boolean is_valid_parentheses(final String input) {
        assert input != null;

        HashMap<Character, Character> charMap = new HashMap<Character ,Character>();
        charMap.put('{', '}');
        charMap.put('[', ']');
        charMap.put('(', ')');
        
        Stack<Character> st = new Stack<Character>();
        for(Character ch: input.toCharArray()) {
            if(charMap.containsKey(ch)) {
                st.push(ch);
            } else if(charMap.containsValue(ch)) {
                if (!st.empty() && ch.equals(charMap.get(st.peek()))) {
                    st.pop();
                }
            }
        }
        return st.empty();
    }
}
