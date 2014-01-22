require 'csv'

fileName = ARGV[0]
isSheFree = ARGV[1]

girls = Array.new

CSV.foreach(fileName) do |row|
	if row[3] == isSheFree
		girls << row
	end
end

girls = girls.sort_by {|e| e[1].to_i}

CSV.open("output_girls.csv", "wb") do |row|
	girls.each do |element|
		row << element
	end
end

puts CSV.read("output_girls.csv", "r").length