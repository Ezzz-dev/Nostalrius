function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 33316, y = 31591, z = 15}, 1949) then
		doRelocate(item:getPosition(),{x = 33328, y = 31592, z = 14})
	end
end

function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 33316, y = 31591, z = 15}, 1949) then
		doRelocate(item:getPosition(),{x = 33328, y = 31592, z = 14})
	end
end