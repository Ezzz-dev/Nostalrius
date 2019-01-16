function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 32225, y = 32276, z = 10}, 1949) then
		doRelocate(item:getPosition(),{x = 32232, y = 32276, z = 09})
		item:getPosition():sendMagicEffect(15)
		Game.sendMagicEffect({x = 32232, y = 32276, z = 09}, 15)
	end
end

function onAddItem(item, tileitem, position)
	if Game.isItemThere({x = 32225, y = 32276, z = 10}, 1949) then
		doRelocate(item:getPosition(),{x = 32232, y = 32276, z = 09})
		item:getPosition():sendMagicEffect(15)
		Game.sendMagicEffect({x = 32232, y = 32276, z = 09}, 15)
	end
end
