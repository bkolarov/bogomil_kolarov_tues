#The one with the hash
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

require 'csv'

fileName = ARGV[0]
outputFileName = fileName.gsub(".csv", "") + "_result.csv"

hash = Hash.new {|hash,k| hash[k] = [[],0]}

CSV.foreach(fileName) do |row|
	valute = row[4].split(" ")[0]
	#sum = hash[valute][1].to_i + row[2].to_i
	hash[valute] = valute, hash[valute][1].to_i + row[2].to_i
end

hash = hash.sort_by {|k,v| v[1].to_i}
hash.each {|k,v| puts v}
CSV.open(outputFileName, "wb") do |row|
	hash.each do |key,value|
		row << value
	end
end
