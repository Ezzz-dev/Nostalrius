function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 32233, y = 32276, z = 9}, 1949) then
		doRelocate(item:getPosition(),{x = 32225, y = 32275, z = 10})
		Game.sendMagicEffect({x = 32233, y = 32276, z = 09}, 15)
		Game.sendMagicEffect({x = 32225, y = 32275, z = 10}, 15)
	end
end

function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 32233, y = 32276, z = 9}, 1949) then
		doRelocate(item:getPosition(),{x = 32225, y = 32275, z = 10})
		Game.sendMagicEffect({x = 32233, y = 32276, z = 09}, 15)
		Game.sendMagicEffect({x = 32225, y = 32275, z = 10}, 15)
	end
end
