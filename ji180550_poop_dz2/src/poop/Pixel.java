package poop;

public class Pixel {
	private int r, g, b, a;
	private boolean active;
	
	public Pixel(int r, int g, int b, int a) {//EXCEPTION: error in pix value?
		this.r = r;
		this.g = g;
		this.b = b;
		this.a = a;
	}
	public Pixel(int r, int g, int b, int a, boolean active) {
		this(r, g, b, a);
		this.active = active;
	}
	
	//getters:
	public int getR() { return r; }
	public int getG() { return g; }
	public int getB() { return b; }
	public int getA() { return a; }
	public boolean getActive() { return active; }
	//setters:
	public void setR(int r) {
		this.r = r;
	}
	public void setG(int g) {
		this.g = g;
	}
	public void setB(int b) {
		this.b = b;
	}
	public void setA(int a) {
		this.a = a;
	}
	public void setActive(boolean active) {
		this.active = active;
	}
	
	//check&Fix //ne treba mi
	public void checkAndFixRGB() {
		if (r > 255) r = 255;
		if (r < 0) r = 0;

		if (g > 255) g = 255;
		if (g < 0) g = 0;

		if (b > 255) b = 255;
		if (b < 0) b = 0;
	}
	
	
}
