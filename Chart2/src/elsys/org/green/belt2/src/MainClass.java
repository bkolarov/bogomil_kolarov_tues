package elsys.org.green.belt2.src;

import java.util.ArrayList;
import java.util.Scanner;

public class MainClass {

	public static void main(String[] args) {
		ArrayList<Chart> list = new ArrayList<Chart>();
		Scanner scan = new Scanner(System.in);
		
		String[] text;
	
		int loopCounter = 0;
		
		while(true) {
			System.out.println("enter line: ");
			text = (scan.next()).split(",");
			
			if(text.length == 1) {
				break;
			}
			
			if(loopCounter % 2 == 0) {
				PieChart p = new PieChart(Integer.parseInt(text[0]),
								Integer.parseInt(text[1]), 
								Integer.parseInt(text[2]));
				
				list.add(p);
			}else {
				BarChart b = new BarChart(Integer.parseInt(text[0]),
						Integer.parseInt(text[1]), 
						Integer.parseInt(text[2]));
				
				list.add(b);
			}
			
		}
		
		for(Chart c: list) {
			System.out.println(c.variable1);
			System.out.println(c.variable2);
			System.out.println(c.variable3);
			
			if(c instanceof PieChart) {
				if(c.variable2 > c.variable1) {
					((PieChart)c).ivan();
				}
			}	
		}
		
		for(Chart c: list) {
			if(c instanceof PieChart) {
				System.out.println(((PieChart)c).getSum());
			}else {
				System.out.println(((BarChart)c).getSum());
			}
		}
		
	}

}
