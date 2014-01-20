package elsys.org.greenBelt.src;

import java.util.ArrayList;
import java.util.Scanner;

public class MainClass {

	public static void main(String[] args) {
		ArrayList<Chart> chart = new ArrayList<Chart>();
		Scanner terminal = new Scanner(System.in);
		
		String[] text;
		
		while(true) {
			System.out.println("enter line: ");
			text = (terminal.next()).split(",");
			
			if(text.length == 1) {
				System.out.println("break loop...");
				break;
			} 
			
			if(text[3].equals('b')) {
				BarChart b = new BarChart(Integer.parseInt(text[0]), 
						Integer.parseInt(text[1]), 
						Integer.parseInt(text[2]));
				chart.add(b);
			}
			
			if(text[3].equals('p')) {
				PieChart p = new PieChart(Integer.parseInt(text[0]), 
						Integer.parseInt(text[1]), 
						Integer.parseInt(text[2]));
				chart.add(p);
				
			}
		}

		for(Chart c:chart ) {
			System.out.println("in second loop");
			if(c instanceof PieChart) {
				System.out.println("c is instance of Pie");
				if(c.value2 > c.value1) {
					((PieChart) c).ivan();
				}
			}
		}
	
		for(Chart c: chart) {
			System.out.println("print all");
			if(c instanceof BarChart) {
				System.out.println("BarChart values:");
			}else {
				System.out.println("PieChart values:");
			}
				System.out.println(c.value1);
				System.out.println(c.value2);
				System.out.println(c.value3);
		}
	}

}
