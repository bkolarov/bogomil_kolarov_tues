require 'csv'

fileName = ARGV[0]
outputFileName = fileName.gsub(".csv", "") + "_result.csv"

champClass = ARGV[1]
selectedChamps = Array.new

CSV.foreach(fileName) do |row|
	if champClass == row[1].split("/")[0] || champClass == row[1].split("/")[1] || champClass == row[1]
		selectedChamps << row[0].gsub("champ_", "").gsub("_", " ") + "," + row[3]
	end
end

selectedChamps = selectedChamps.sort_by do |x| 
	x.split(",")[1].to_i
end

CSV.open(outputFileName, "wb") do |row| 
	selectedChamps.each do |element|
		row << [element.split(",")[0], element.split(",")[1]]
	end
end

