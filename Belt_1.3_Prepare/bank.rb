#номер/дата/дебит/кредит/получател-наредител/забележка(PAYPAL,OMV,EUROPCAR,EKO,LUKOIL,GOOGLE и др.).

require 'csv'
require 'date'

fileName = ARGV[0]
note = ARGV[1]
outputFileName = ARGV[2]

dates = []

CSV.foreach(fileName) do |row|
	next if dates.include? row[1].split("/")

	if row[5] == note
		dates << row[1].split("/")
	end
end

dates.sort {|a,b| a <=> b}

CSV.open(outputFileName, "wb") do |f|
	dates.each do |x|
		f << [x[0],x[1],x[2]]
	end
end