function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
		if Game.isItemThere({x = 33368, y = 31756, z = 11}, 355) then
			Game.transformItemOnMap({x = 33368, y = 31756, z = 11}, 355, 386)
		end
	end
end

function onStepOut(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		Game.transformItemOnMap({x = 33368, y = 31756, z = 11}, 386, 355)
	end
end
