function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 32957, y = 32076, z = 07})
		creature:getPlayer():setTown(Town("Venore"))
		Game.sendMagicEffect({x = 32957, y = 32076, z = 07}, 13)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32952, y = 32035, z = 07})
	Game.sendMagicEffect({x = 32952, y = 32035, z = 07}, 14)
end
