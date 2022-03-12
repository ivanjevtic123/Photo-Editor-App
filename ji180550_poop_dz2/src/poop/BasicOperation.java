package poop;

import poop.Operation.OperationType;

public class BasicOperation extends Operation {

	private boolean arrOfOperations = false;//u exe CompositeOp mzd koristiti
	private boolean lastOperation = false;
	private int num;
	private OperationType type;
	
	
	
	public BasicOperation(OperationType type, int num, boolean selExists, boolean opArr, boolean last) { 
		super(selExists);
		this.type = type;
		this.arrOfOperations = opArr;
		this.lastOperation = last;
		if(type == OperationType.ADD || type == OperationType.SUB || 
		   type == OperationType.INVSUB || type == OperationType.MUL || 
		   type == OperationType.DIV || type == OperationType.INVDIV || 
	       type == OperationType.POW || type == OperationType.MIN || 
	       type == OperationType.MAXIM) 
		{
			this.num = num;		
		}
		if(type == OperationType.LOG || type == OperationType.ABS ||
		   type == OperationType.INV || type == OperationType.GRAY ||
	  	   type == OperationType.BNW)
		{
				this.num = 0;//arg nepotreban
		}
	    if(type == OperationType.MED) 
		{//dodaj
			this.num = 0;//arg nepotreban	
		}
		
	}
	
	@Override
	public void execution(Pixel curr) { //switch na c++ napraviti po TypeOp
		int ordinal = type.ordinal();//od 0???
		System.loadLibrary("dz1");
		//System.out.println("" + curr.getR() + ":" + curr.getG() + ":" + curr.getB() + ":" + curr.getA());
		int[] rgba = this.exeCpp(curr.getR(), curr.getG(), curr.getB(), curr.getA(), curr.getActive(),
				this.num, this.selectionExists, this.arrOfOperations, this.lastOperation, ordinal);//rgbaf
		//System.out.println("" + rgba[0] + ":" + rgba[1] + ":" + rgba[2] + ":" + rgba[3]);
		curr.setR(rgba[0]);//CAST MORA
		curr.setG(rgba[1]);
		curr.setB(rgba[2]);
		curr.setA(rgba[3]);
	}
	
	@Override
	public void setLastFlag(boolean flag) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public OperationType getOperationType() {
		return type;
	}
	
	public void setType(OperationType type) {
		this.type = type;
	}
	
	@Override
	public int getNum() {
		return num;
	}
	
	//c++ //sa arg raspakovanim //RGB DA VRATI, INT[3], KTR ZA PIX IZNAD
	public native int[] exeCpp(int r, int g, int b, int a, boolean selActive,
			int number, boolean selExists, boolean arrOfOp, boolean lastOp, int ordinal);
	
}
