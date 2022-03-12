package poop;

public class Layer {

	protected Pixel [][] matrix;
	protected int w, h;
	String path;
	private boolean active;
	private boolean visible;
	
	
	
	public Layer() {
	
	}
	public Layer(int w, int h, String path) {
		this.w = w;
		this.h = h;
		this.path = path;
		this.matrix = new Pixel[h][w];
	}
	public Layer(Layer l) {
		this.w = l.w;
		this.h = l.h;
		this.active = l.active;
		this.visible = l.visible;
	}
	
	//getters:
	public int getW() {
		return w;
	}
	public int getH() {
		return h;
	}
	public boolean getActive() {
		return active;
	}
	public boolean getVisible() {
		return visible;
	}
	//setters:
	public void setW(int w) {
		this.w = w;
	}
	public void setH(int h) {
		this.h = h;
	}
	public void setActive(boolean active) {
		this.active = active;
	}
	public void setVisible(boolean visible) {
		this.visible = visible;
	}
	
	
}
