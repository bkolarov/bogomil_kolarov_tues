require 'csv'
require 'date'

fileName = ARGV[0]
outputFileName = fileName.gsub(".csv", "") + "_result.csv"

champsArray = Array.new
outputArray = Array.new


CSV.foreach(fileName) do |row|
	champsArray << row
end

champsArray = champsArray.sort_by {|e| Date.parse(e[2].split("date_")[1])}

outputArray[0] = champsArray[0][0].gsub("champ_", "").gsub("_", " ") + "," + champsArray[0][2].gsub("date_", "")
outputArray[1] = champsArray[-1][0].gsub("champ_", "").gsub("_", " ") + "," + champsArray[-1][2].gsub("date_", "")

outputArray = outputArray.sort_by {|e| Date.parse(e.split(",")[1])}

CSV.open(outputFileName, "wb") do |row|
	outputArray.each do |element|
		row << [element.split(",")[0],element.split(",")[1]]
	end
end