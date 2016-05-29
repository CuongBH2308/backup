public class SynchronizedColor {
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
    public SynchronizedColor(int red, int green, int blue, final String name) {
        check(red);
        check(green);
        check(blue);
        this.red = red;
        this.green = green;
        this.blue = blue;
        this.name = name;
    }
    
    // getters
    public synchronized int getRed() { return red; }
    public synchronized int getGreen() { return green; }
    public synchronized int getBlue() { return blue; }
    public synchronized String getName() { return name; }
    
    // setters
    public void setRed(int red) { check(red); synchronized(this) { this.red = red;} }
    public void setGreen(int green) { check(red); synchronized(this) {this.green = green;} }
    public void setBlue(int blue) { check(red); synchronized(this) { this.blue = blue; }}
    public void setName(final String name) { assert name != null; synchronized(this) { this.name = name; }}
    
    // operations
    public synchronized int getRGB() {
        return ((red << 16) | (green << 8) | blue);
    }
    
    public synchronized void invert() {
        red = 255 - red;
        blue = 255 - blue;
        green = 255 - green;
        name = "Inverse of " + name;
    }
    
    public synchronized String toString() {
        return name + "(" + red + "," + green + "," + blue + ")";
    }
    
    // Testing
    public static void main(String[] args) {
        System.out.println(new SynchronizedColor(0, 0, 0, "Black"));
    }
 
}