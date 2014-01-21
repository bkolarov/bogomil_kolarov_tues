require 'csv'
require 'date'

fileName = ARGV[0]
outputFileName = ARGV[0].split('.')[0] + "_result.csv"

array = Array.new
outputArray = Array.new

CSV.foreach(fileName) do |row|
	array << row[2].split('_')[1] + "," + row[0].gsub("champ_", "").gsub("_", " ")
end

array = array.sort_by {|x| Date.parse(x.split(',')[0]) }

outputArray[0] = array[0]
outputArray[1] = array[1]
outputArray[2] = array[-1]

outputArray = outputArray.sort_by {|x| x.split(',')[1]}

CSV.open(outputFileName, "wb") do |row|
	outputArray.each do |element|
		row << [element.split(',')[0], element.split(',')[1]]
		
	end
end