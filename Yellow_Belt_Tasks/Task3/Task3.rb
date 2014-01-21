require 'csv'

fileName = ARGV[0]
age = ARGV[1]
ageOlder = age.to_i + 2
ageYounger = age.to_i - 2

array = Array.new

CSV.foreach(fileName) do |row|
	if ageOlder == row[1].to_i || ageYounger == row[1].to_i 
		if row[3] == "Sama"
			array << [row[0],row[1],row[2],row[3], row[4]]
		end
	end
end

array = array.sort_by {|x| x[1]}

CSV.open("momicheta_result.csv", "wb") do |f|
	array.each do |element|
		f << element
	end
end