function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 32360, y = 31782, z = 07})
		creature:getPlayer():setTown(Town("Carlin"))
		Game.sendMagicEffect({x = 32360, y = 31782, z = 07}, 13)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32360, y = 31780, z = 08})
	Game.sendMagicEffect({x = 32360, y = 31780, z = 08}, 14)
end
