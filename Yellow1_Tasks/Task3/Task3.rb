require 'csv'

fileName = ARGV[0]
outputFileName = fileName.gsub(".csv", "") + "_result.csv"

minDebit = ARGV[1].to_f

outputArray = Array.new

CSV.foreach(fileName) do |row|
	if row[2].to_f > minDebit
		outputArray << row
	end
end

outputArray = outputArray.sort_by {|e| e[2].to_f}
outputArray = outputArray.reverse

CSV.open(outputFileName, "wb") do |row|
	outputArray.each do |element|
		row << element
	end
end