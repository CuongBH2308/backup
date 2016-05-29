public class Color {
    private int red;
    private int green;
    private int blue;
    private String name;
    
    private void check(int element) {
        if(element < 0 || red > 255) {
            throw new IllegalArgumentException();
        }
    }
    
    // constructor
    public Color(int red, int green, int blue, final String name) {
        setRed(red);
        setGreen(green);
        setBlue(blue);
        setName(name);
    }
    
    // getters
    public int getRed() { return red; }
    public int getGreen() { return green; }
    public int getBlue() { return blue; }
    public String getName() { return name; }
    
    // setters
    public void setRed(int red) { check(red); this.red = red; }
    public void setGreen(int green) { check(red); this.green = green; }
    public void setBlue(int blue) { check(red); this.blue = blue; }
    public void setName(final String name) { assert name != null; this.name = name; }
    
    // operations
    public int getRGB() {
        return ((red << 16) | (green << 8) | blue);
    }
    
    public void invert() {
        red = 255 - red;
        blue = 255 - blue;
        green = 255 - green;
        name = "Inverse of " + name;
    }
    
    public String toString() {
        return name + "(" + red + "," + green + "," + blue + ")";
    }
    
    // Testing
    public static void main(String[] args) {
        System.out.println(new Color(0, 0, 0, "Black"));
    }
 
}