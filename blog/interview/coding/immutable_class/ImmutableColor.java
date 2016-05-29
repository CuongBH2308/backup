public final class ImmutableColor {
    private final int red;
    private final int green;
    private final int blue;
    private final String name;
    
    private void check(int element) {
        if(element < 0 || red > 255) {
            throw new IllegalArgumentException();
        }
    }
    
    // constructor
    public ImmutableColor(int red, int green, int blue, final String name) {
        check(red);
        check(green);
        check(blue);
        this.red = red;
        this.green = green;
        this.blue = blue;
        this.name = name;
    }
    
    // getters
    public int getRed() { return red; }
    public int getGreen() { return green; }
    public int getBlue() { return blue; }
    public String getName() { return name; }
    
    // operations
    public int getRGB() {
        return ((red << 16) | (green << 8) | blue);
    }
    
    public ImmutableColor invert() {
        return new ImmutableColor(255-red, 255-green, 255-blue, "Inverse of " + name);
    }
    
    public String toString() {
        return name + "(" + red + "," + green + "," + blue + ")";
    }
    
    // Testing
    public static void main(String[] args) {
        System.out.println(new ImmutableColor(0, 0, 0, "Black"));
        System.out.println(new ImmutableColor(0, 0, 0, "Black").invert());
    }
 
}