require 'csv'

fileName = ARGV[0]
cpu = ARGV[1].downcase

laptops = Array.new

CSV.foreach(fileName) do |row|
	if row[1].downcase == cpu
		laptops << row
	end
end

laptops = laptops.sort_by {|e| e[2].to_i}

CSV.open("laptops_processor_result.csv", "wb") do |row|
	laptops.each do |element|
		row << element
	end
end