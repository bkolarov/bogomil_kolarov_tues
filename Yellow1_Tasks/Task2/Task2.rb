require 'csv'

fileName = ARGV[0]
outputFileName = fileName.gsub(".csv", "") + "_result.csv"

hash = {}

CSV.foreach(fileName) do |row|
	valute = row[4].split(" ")[0]
	hash[valute] = hash[valute].to_i + row[2].to_i
end

hash = hash.sort_by {|k,v| v.to_i}
puts hash
CSV.open(outputFileName, "wb") do |row|
	hash.each do |key,value|
		row << [key, value]
	end
end