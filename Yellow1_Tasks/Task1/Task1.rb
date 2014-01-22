require 'csv'

fileName = ARGV[0]
outputFileName = fileName.gsub(".csv", "") + "_result.csv"
valuta = ARGV[1]

bankArray = Array.new

CSV.foreach(fileName) do |row|

	if row[4].split(" ")[0] == valuta
		bankArray << row
	end
end

bankArray = bankArray.sort_by {|e| e[2].to_i}

CSV.open(outputFileName, "wb") do |row|
	bankArray.each do |element|
		row << element
	end
end