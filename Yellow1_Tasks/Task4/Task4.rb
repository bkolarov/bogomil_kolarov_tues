require 'csv'
require 'date'

fileName = ARGV[0]
outputFileName = fileName.gsub(".csv", "") + "_result.csv"
date = Date.parse(ARGV[1])

beforeDateArray = Array.new

CSV.foreach(fileName) do |row|
	if Date.parse(row[1]) < date
		beforeDateArray << row
	end
end

beforeDateArray = beforeDateArray.sort_by {|e| e[2].to_i}
beforeDateArray = beforeDateArray.reverse

CSV.open(outputFileName, "wb") do |row|
	beforeDateArray.each do |element|
		row << element
	end
end