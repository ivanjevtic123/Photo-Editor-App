package poop;

public class Rectangle {

	private int posX, posY; //pozicija levog gornjeg ugla
	private int height, width;
	private boolean status = true; //da li selektovani pixel selectujem ili unselectujem


	
	public Rectangle(int x, int y, int w, int h) {
		this.posX = x;
		this.posY = y;
		this.width = w;
		this.height = h;
	}

	public void setActiveStatus() {
		status = true;
	}
	
	public void setNotActiveStatus() {
		status = false;
	}
	
	public boolean getStatus() {
		return status;
	}
	
	public boolean contains(int i, int j) {
		return (i>=posX) && (i<=posX + width) && (j>=posY) && (j<=posY + height);
	}

	//getters:
	public int getX() {
		return posX;
	}
	public int getY() {
		return posY;
	}
	public int getWidth() {
		return width;
	}
	public int getHeight() {
		return height;
	}
	
	@Override
	public String toString() {
		return  "" + posX + " " + posY + " " + height + " " + width + " " + status;
	}
}
