function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 32803, y = 31584, z = 01},2773) and Game.isItemThere ({x = 32805, y = 31584, z = 01},2773) and Game.isItemThere ({x = 32802, y = 31584, z = 01},2772) and Game.isItemThere ({x = 32804, y = 31584, z = 01}, 2772) then 
		doRelocate(item:getPosition(),{x = 32701, y = 31639, z = 06})
		Game.sendMagicEffect({x = 32701, y = 31639, z = 06}, 11)
	else
		doRelocate(item:getPosition(),{x = 32803, y = 31587, z = 01})
		Game.sendMagicEffect({x = 32803, y = 31587, z = 01}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32803, y = 31587, z = 01})
	Game.sendMagicEffect({x = 32803, y = 31587, z = 01}, 11)
end
