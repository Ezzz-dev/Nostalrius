function onAddItem(item, tileitem, position)
	if (item:getType():isMovable() and Tile(position):getThingCount() == 2) or
		(tileitem:getId() >= 4874 and tileitem:getId() <= 4880) then
		item:getPosition():sendMagicEffect(9)
		item:remove()
	end
	return true
end