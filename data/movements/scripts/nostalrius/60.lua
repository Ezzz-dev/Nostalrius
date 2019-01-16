function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Game.isItemThere({x = 32563, y = 31957, z = 01},3114) and Game.isItemThere ({x = 32565, y = 31957, z = 01},3114) and Game.isItemThere ({x = 32567, y = 31957, z = 01},3114) and Game.isItemThere ({x = 32569, y = 31957, z = 01},3114) then 
		doRelocate(item:getPosition(),{x = 32479, y = 31923, z = 07})
		Game.sendMagicEffect({x = 32563, y = 31957, z = 01}, 10)
		Game.sendMagicEffect({x = 32565, y = 31957, z = 01}, 10)
		Game.sendMagicEffect({x = 32567, y = 31957, z = 01}, 10)
		Game.sendMagicEffect({x = 32569, y = 31957, z = 01}, 10)
		Game.removeItemOnMap({x = 32563, y = 31957, z = 01}, 3114)
		Game.removeItemOnMap({x = 32565, y = 31957, z = 01}, 3114)
		Game.removeItemOnMap({x = 32567, y = 31957, z = 01}, 3114)
		Game.removeItemOnMap({x = 32569, y = 31957, z = 01}, 3114)
		Game.createItem(2121, 1, {x = 32563, y = 31957, z = 01})
		Game.createItem(2121, 1, {x = 32565, y = 31957, z = 01})
		Game.createItem(2121, 1, {x = 32567, y = 31957, z = 01})
		Game.createItem(2121, 1, {x = 32569, y = 31957, z = 01})
		Game.sendMagicEffect({x = 32566, y = 31957, z = 01}, 3)
	end
end
