package elsys.org.green.belt2.src;

public class PieChart extends Chart implements IvanPetrov {
	private int sum;
	
	public PieChart(int variable1, int variable2, int variable3) {
		super(variable1, variable2, variable3);
	}

	public void ivan() {
		this.variable2 -= variable1;	
	}
	
	private void setSum() {
		this.sum = this.variable1 + this.variable2 + this.variable3;
	}
	
	public int getSum() {
		setSum();
		return sum;
	}
	
}
