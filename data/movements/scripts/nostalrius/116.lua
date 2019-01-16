function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 33145, y = 32862, z = 07}, 3465) and creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 33151, y = 32864, z = 07})
		item:getPosition():sendMagicEffect(15)
		Game.sendMagicEffect({x = 33151, y = 32864, z = 07}, 15)
	else
		doRelocate(item:getPosition(),{x = 33145, y = 32863, z = 07})
		item:getPosition():sendMagicEffect(15)
		Game.sendMagicEffect({x = 33145, y = 32863, z = 07}, 15)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33145, y = 32863, z = 07})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 33145, y = 32863, z = 07}, 15)
end
