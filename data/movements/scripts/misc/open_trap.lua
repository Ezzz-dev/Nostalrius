function onRemoveItem(item, tileitem, position)
	if item:getPosition():getDistance(position) > 0 then
		item:transform(3481, 1)
		item:decay()
		item:getPosition():sendMagicEffect(3)
	end
	return true
end