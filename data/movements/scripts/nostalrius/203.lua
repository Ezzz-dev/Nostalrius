function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 32649, y = 31925, z = 11})
		creature:getPlayer():setTown(Town("Kazordoon"))
		Game.sendMagicEffect({x = 32649, y = 31925, z = 11}, 13)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32647, y = 31925, z = 12})
	Game.sendMagicEffect({x = 32647, y = 31925, z = 12}, 14)
end
