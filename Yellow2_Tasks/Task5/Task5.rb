require 'csv'
require 'date'

fileName = ARGV[0]
note = ARGV[1]
outputFileName = ARGV[2]

selectedArray = Array.new
hash = {}

CSV.foreach(fileName) do |row|
	if row[5] == note
		hash[row[1]] = row
	end
end

hash.each do |k,v|
	selectedArray << v[1]

end

selectedArray = selectedArray.sort_by {|e| Date.parse(e)}

CSV.open(outputFileName, "wb") do |row|
	selectedArray.each do |element|
		row << [element]
	end
end