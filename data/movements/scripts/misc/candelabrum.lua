function onRemoveItem(item, tileitem, position)
	if item:getPosition():getDistance(position)  > 0 then
		item:transform(2912, 1)
		item:decay()
	end
	return true
end