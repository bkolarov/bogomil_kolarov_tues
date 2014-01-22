package elsys.org.green.belt2.src;

public class BarChart extends Chart {
	private int sum;
	
	public BarChart(int variable1, int variable2, int variable3) {
		super(variable1, variable2, variable3);
	}

	private void setSum() {
		this.sum = this.variable1 + this.variable2 + this.variable3;
	}
	
	public int getSum() {
		setSum();
		return sum;
	}
}
